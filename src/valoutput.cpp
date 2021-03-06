/* valoutput.cpp:    print values read from victim process memory
 *
 * Copyright (c) 2012..13, by:  Sebastian Riemer
 *    All rights reserved.     <sebastian.riemer@gmx.de>
 *
 * powered by the Open Game Cheating Association
 *
 * This file may be used subject to the terms and conditions of the
 * GNU General Public License Version 2, or any later version
 * at your option, as published by the Free Software Foundation.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <vector>
#include <cstring>

// local includes
#include "valoutput.h"


static void output_mem_val (CfgEntry *cfg_en, void *mem_offs, bool is_dynmem)
{
	DynMemEntry *dynmem;
	double tmp_dval;
	float  tmp_fval;
	i32 hexfloat;

	if (cfg_en->ptrmem) {
		dynmem = cfg_en->ptrmem->dynmem;
		if (dynmem && dynmem->v_maddr.size() > 1)
			cout << " -> " << cfg_en->name << "[" << dynmem->pr_idx << "]"
			     << " at " << hex << PTR_ADD(void *, cfg_en->addr, mem_offs)
			     << ", Data: 0x";
		else
			cout << " -> " << cfg_en->name << " at " << hex
			     << PTR_ADD(void *, cfg_en->addr, mem_offs)
			     << ", Data: 0x";
	} else if (is_dynmem && cfg_en->dynmem->v_maddr.size() > 1) {
		cout << cfg_en->name << "[" << cfg_en->dynmem->pr_idx << "]"
		     << " at " << hex << PTR_ADD(void *, cfg_en->addr, mem_offs)
		     << ", Data: 0x";
	} else {
		cout << cfg_en->name << " at " << hex
		     << PTR_ADD(void *, cfg_en->addr, mem_offs)
		     << ", Data: 0x";
	}

	if (cfg_en->is_float) {
		memcpy(&tmp_dval, &cfg_en->old_val, sizeof(i64));
		if (cfg_en->size == 32) {
			tmp_fval = (float) tmp_dval;
			memcpy(&hexfloat, &tmp_fval, sizeof(i32));
			cout << hex << hexfloat;
		} else {
			cout << hex << (i64) cfg_en->old_val;
		}
		cout << " (" << dec << tmp_dval << ")" << endl;
	} else {
		if (cfg_en->size == 64)
			cout << hex << (i64) cfg_en->old_val;
		else
			cout << hex << (i32) cfg_en->old_val;

		if (cfg_en->is_signed)
			cout << " (" << dec << cfg_en->old_val << ")" << endl;
		else
			cout << " (" << dec << (u64) cfg_en->old_val << ")" << endl;
	}
}

static void output_ptrmem_values (CfgEntry *cfg_en)
{
	DynMemEntry *dynmem = cfg_en->ptrtgt->dynmem;
	void *mem_offs;
	list<CfgEntry*> *cfg_act = &cfg_en->ptrtgt->cfg_act;
	list<CfgEntry*>::iterator it;

	mem_offs = cfg_en->ptrtgt->v_offs[dynmem->pr_idx];
	cout << " -> *" << cfg_en->ptrtgt->name << "["
	     << dynmem->pr_idx << "]"
	     << " = " << hex << mem_offs << dec << endl;

	list_for_each (cfg_act, it) {
		cfg_en = *it;
		cfg_en->old_val = cfg_en->v_oldval[dynmem->pr_idx];
		output_mem_val(cfg_en, mem_offs, false);
	}
}

void output_mem_values (list<CfgEntry*> *cfg_act)
{
	list<CfgEntry*>::iterator it;
	CfgEntry *cfg_en;
	DynMemEntry *old_dynmem = NULL;
	vector<void *> *mvec;
	void *mem_offs = NULL;
	bool is_dynmem;

	list_for_each (cfg_act, it) {
		cfg_en = *it;
		is_dynmem = false;
		if (cfg_en->dynmem) {
			mvec = &cfg_en->dynmem->v_maddr;
			if (mvec->empty()) {
				continue;
			} else {
				if (cfg_en->dynmem->pr_idx >= mvec->size())
					cfg_en->dynmem->pr_idx = mvec->size() - 1;
				mem_offs = mvec->at(cfg_en->dynmem->pr_idx);
				cfg_en->old_val =
					cfg_en->v_oldval[cfg_en->dynmem->pr_idx];
				is_dynmem = true;
				if (cfg_en->dynmem != old_dynmem) {
					cout << "*" << cfg_en->dynmem->name << "["
					     << cfg_en->dynmem->pr_idx << "]" << " = "
					     << hex << mem_offs << dec << ", "
					     << mvec->size() << " obj." << endl;
						old_dynmem = cfg_en->dynmem;
				}
			}
		} else {
			mem_offs = NULL;
		}
		output_mem_val(cfg_en, mem_offs, is_dynmem);
		if (cfg_en->ptrtgt)
			output_ptrmem_values(cfg_en);
	}
}
