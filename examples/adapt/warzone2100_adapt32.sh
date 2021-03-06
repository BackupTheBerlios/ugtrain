#!/bin/bash

# Tested with: Warzone 2100 2.3.8, 2.3.9, 3.1.0, 3.1.1

# We already know that warzone2100 is a 32-bit C++ application and that
# the Droid and Structure classes are allocated with _Znwj() or malloc().
# From previous discovery runs we already know the malloc sizes.

CWD=`dirname $0`
cd "$CWD"
APP_PATH="$1"
APP_VERS=`${APP_PATH} --version | grep -o "\([0-9]\+\\.\)\{2\}[0-9]\+"`
RC=0

. _common_adapt.sh

if [ "$APP_VERS" == "2.3.8" -o "$APP_VERS" == "2.3.9" ]; then
  get_malloc_code "$APP_PATH" "\<malloc@plt\>" "0x36c" 3 3 3
  if [ $RC -ne 0 ]; then exit 1; fi
else
  get_malloc_code "$APP_PATH" "\<_Znwj@plt\>" "0x2fc," 3 3 3
  if [ $RC -ne 0 ]; then exit 1; fi
fi

CODE_ADDR1="$CODE_ADDR"

############################################

if [ "$APP_VERS" == "2.3.8" -o "$APP_VERS" == "2.3.9" ]; then
  get_malloc_code "$APP_PATH" "\<malloc@plt\>" "0x128" 3 7 7
  if [ $RC -ne 0 ]; then exit 1; fi
else
  get_malloc_code "$APP_PATH" "\<_Znwj@plt\>" "0x16c," 3 7 7
  if [ $RC -ne 0 ]; then exit 1; fi
fi

CODE_ADDR2="$CODE_ADDR"

RESULT=`echo "2;Droid;0x$CODE_ADDR1;Structure;0x$CODE_ADDR2"`
echo "$RESULT"

# Should return something like this:
# 813ce5e:	c7 04 24 6c 03 00 00 	movl   $0x36c,(%esp)
# 813ce65:	e8 76 73 f3 ff       	call   80741e0 <malloc@plt>
# 813ce6a:	85 c0                	test   %eax,%eax

# This shows us that 0x813ce6a is the relevant Droid code address.

# We can jump directly to stage 4 of the discovery with that and leave the
# heap start and end offsets at 0x0 (NULL) as we already know the unique
# code address and malloc size per memory class.
