//®ɽ������
//lestat for dtxy 2001
//����
 
#include <ansi.h>
inherit NPC;
void create()
{
   set_name(MAG"����"NOR, ({"zi long", "zi", "long"}));
   set("age", 700);
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
   set("max_kee", 6200);
   set("max_sen", 6200);
   set("force", 18000);
   set("max_force", 9000);
   set("force_factor", 450);
   set("mana", 18000);
   set("max_mana", 9000);
   set("mana_factor", 450);
   set_skill("unarmed", 550+random(50));
   set_skill("parry", 550+random(50));
   set_skill("dragonfight", 550+random(50));
   set_skill("dragonstep", 550);
   map_skill("unarmed", "dragonfight");
   map_skill("dodge", "dragonstep");
   set("combat_exp", 50000000);
   set_weight(900000);
   setup();
}

