//®ɽ������
//lestat for dtxy 2001
//����
 
#include <ansi.h>
inherit NPC;
void create()
{
   set_name(HIW"����"NOR, ({"bai long", "bai", "long"}));
   set("age", 900);
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
   set("max_kee", 8200);
   set("max_sen", 8200);
   set("force", 18000);
   set("max_force", 10000);
   set("force_factor", 600);
   set("mana", 18000);
   set("max_mana", 10000);
   set("mana_factor", 600);
   set_skill("unarmed", 750+random(50));
   set_skill("parry", 750+random(50));
   set_skill("dragonfight", 750+random(50));
   set_skill("dragonstep", 750);
   map_skill("unarmed", "dragonfight");
   map_skill("dodge", "dragonstep");
   set("combat_exp", 70000000);
   set_weight(900000);
   setup();
}

