//庐山升龙霸
//lestat for dtxy 2001
//赤龙
 
#include <ansi.h>
inherit NPC;
void create()
{
   set_name(RED"橙龙"NOR, ({"cheng long", "cheng", "long"}));
   set("age", 300);
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
   set("max_kee", 2200);
   set("max_sen", 2200);
   set("force", 6000);
   set("max_force", 3000);
   set("force_factor", 150);
   set("mana", 6000);
   set("max_mana", 3000);
   set("mana_factor", 150);
   set_weight(600000);
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

