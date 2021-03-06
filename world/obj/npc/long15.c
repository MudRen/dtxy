//庐山升龙霸
//lestat for dtxy 2001
//青龙
 
#include <ansi.h>
inherit NPC;
void create()
{
   set_name(CYN"青龙"NOR, ({"qing long", "qing", "long"}));
   set("age", 500);
   set("long", "一只模样高大，极有气势的龙。\n");
   set("str", 100);
   set("cor", 40);
   set("con", 40);
   set("cps", 40);
   set("spi", 40);
   set("int", 40);
   set_temp("apply/damage", 150);
   set_temp("apply/attack", 150);
   set_temp("apply/armor", 800);
   set("max_kee", 4200);
   set("max_sen", 4200);
   set("force", 12000);
   set("max_force", 6000);
   set("force_factor", 300);
   set("mana", 12000);
   set("max_mana", 6000);
   set("mana_factor", 300);
   set_weight(900000);
}

void init_data(int skill, int wx)
{
	set_skill("unarmed", skill);
	set_skill("parry", skill);
	set_skill("dragonfight", skill);
	set_skill("dragonstep", skill);
	map_skill("unarmed", "dragonfight");
	map_skill("dodge", "dragonstep");
	set("combat_exp", wx);
	setup();
}
