//®ɽ������
//lestat for dtxy 2001
//����
 
#include <ansi.h>
inherit NPC;
void create()
{
   set_name(HIR"����"NOR, ({"chi long", "chi", "long"}));
   set("age", 300);
   set("long", "һֻģ���ߴ󣬼������Ƶ�����\n");
   set("str", 100);
   set("cor", 40);
   set("con", 40);
   set("cps", 40);
   set("spi", 40);
   set("int", 40);
   set_temp("apply/damage", 150);
   set_temp("apply/attack", 150);
   set_temp("apply/armor", 800);
   set("max_kee", 1200);
   set("max_sen", 1200);
   set("force", 4000);
   set("max_force", 2000);
   set("force_factor", 100);
   set("mana", 4000);
   set("max_mana", 2000);
   set("mana_factor", 100);
   set_weight(500000);
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
