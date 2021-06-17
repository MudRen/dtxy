#include <ansi.h>
#include "/d/obj/newitem/newitemname.c"
#define TZNUMBER 8

mapping name_sxname = (["kee":"��Ѫ","sen":"����","armor":"����","parry":"�ֵ�","dodge":"�Ṧ","armor_vs_force":"�ڹ�����"]);
mapping name_tzsx1  = (["kee":500,  "sen":500,  "armor":100, "parry":50, "dodge":50]);
mapping name_tzsx2  = (["kee":1000, "sen":1000, "armor":150, "parry":75, "dodge":75]);
mapping name_tzsx3  = (["kee":1500, "sen":1500, "armor":200, "parry":100,"dodge":100]);
mapping name_tzsx4  = (["kee":2000, "sen":2000, "armor":250, "parry":125,"dodge":125]);
mapping name_tzsx5  = (["kee":2500, "sen":2500, "armor":300, "parry":150,"dodge":150]);
mapping name_tzsx6  = (["kee":3000, "sen":3000, "armor":350, "parry":175,"dodge":175]);
mapping name_tzsx7  = (["kee":3500, "sen":3500, "armor":400, "parry":200,"dodge":200]);
mapping name_tzsx8  = (["kee":4000, "sen":4000, "armor":450, "parry":225,"dodge":225]);
mapping name_tzsx9  = (["kee":5000, "sen":5000, "armor":500, "parry":250,"dodge":250,"armor_vs_force":100]);
mapping name_tzsx10 = (["kee":6000, "sen":6000, "armor":600, "parry":300,"dodge":300,"armor_vs_force":150]);
mapping name_tzsx11 = (["kee":7000, "sen":7000, "armor":700, "parry":350,"dodge":350,"armor_vs_force":200]);
mapping name_tzsx12 = (["kee":8000, "sen":8000, "armor":800, "parry":400,"dodge":400,"armor_vs_force":250]);
mapping name_tzsx13 = (["kee":9000, "sen":9000, "armor":900, "parry":450,"dodge":450,"armor_vs_force":300]);
mapping name_tzsx14 = (["kee":10000,"sen":10000,"armor":1000,"parry":500,"dodge":500,"armor_vs_force":500]);
mapping name_tzsx=
([
1:name_tzsx1,
2:name_tzsx2,
3:name_tzsx3,
4:name_tzsx4,
5:name_tzsx5,
6:name_tzsx6,
7:name_tzsx7,
8:name_tzsx8,
9:name_tzsx9,
10:name_tzsx10,
11:name_tzsx11,
12:name_tzsx12,
13:name_tzsx13,
14:name_tzsx14
]);

void equip_mod(object ob, object owner)
{
	int level = ob->query("mod/level");
	mapping applied_prop,stats;
	string *keys;
	string msg;
	int i;
	if (!level)
		return;
	owner->add_temp("mod/level_"+level,1);
	if (owner->query_temp("mod/level_"+level) == TZNUMBER && !owner->query_temp("mod/level"))
	{
		owner->set_temp("mod/level",level);
		stats = name_tzsx[level];
		keys = keys(stats);
		for(i = 0; i<sizeof(keys); i++)
		{
			if (keys[i] == "kee" || keys[i] == "sen")
			{
/*
				owner->add(keys[i],stats[keys[i]]);
				owner->add("max_"+keys[i],stats[keys[i]]);
				owner->add("eff_"+keys[i],stats[keys[i]]);
*/
			} else {
				applied_prop = owner->query_temp("apply");
				applied_prop[keys[i]] += stats[keys[i]]; 
			}
		}
		message_vision("$Nװ����"+name_zbtz[level][0]+NOR"��װ�������ӣ������Լ��޵���!\n", owner);
	}
}

void unequip_mod(object ob, object owner)
{
	int level = ob->query("mod/level");
	mapping applied_prop,stats;
	string *keys;
	string msg;
	int i;
	if (!level)
		return;
	owner->add_temp("mod/level_"+level,-1);
	if (owner->query_temp("mod/level_"+level)+1 == TZNUMBER && owner->query_temp("mod/level"))
	{
		owner->delete_temp("mod/level");
		stats = name_tzsx[level];
		keys = keys(stats);
		for(i = 0; i<sizeof(keys); i++)
		{
			if (keys[i] == "kee" || keys[i] == "sen")
			{
/*
				owner->add(keys[i],-stats[keys[i]]);
				owner->add("max_"+keys[i],-stats[keys[i]]);
				owner->add("eff_"+keys[i],-stats[keys[i]]);
                               if (owner->query(keys[i]) <0) owner->set(keys[i],0);
							  if (owner->query("max_"+keys[i])<0) owner->set("max_"+keys[i],0);
							  if (owner->query("eff_"+keys[i])<0) owner->set("eff_"+keys[i],0);
*/
			} else {
				applied_prop = owner->query_temp("apply");
				applied_prop[keys[i]] += -stats[keys[i]]; 

			}
		}
		message_vision("$Nж����"+name_zbtz[level][0]+NOR"��װ!\n", owner);
	}
}

string print_mod(object ob,object owner)
{
	int level = ob->query("mod/level");
	mapping applied_prop,stats;
	string *keys;
	string msg = "��װ����:";
	int i;
	if (!level)		
		return msg;
	stats = name_tzsx[level];
	keys = keys(stats);
	for(i = 0; i<sizeof(keys); i++)
	{
if (keys[i] == "kee" || keys[i]=="sen")
continue;
		msg += name_sxname[keys[i]]+":"+stats[keys[i]]+" ";
	}
	msg += "\n============================================\n";
	return msg;
}
