inherit NPC;
#include "huoyannpc2.h"

void create()
{
   set_name("ڼʥ���",({"xusheng zhenjun","zhenjun","xianguan","xian",}));
   set("long","���𱣻���ʴ�۵��������¼������������ޱȡ�.\n");
   set("per",23);
   set("str",30);
   set_skill("force",160);
   set_skill("dodge",200);
   set_skill("baguazhen",183);
   set_skill("parry",171);
   set_skill("spells",170);
   set_skill("unarmed",185);
   set_skill("wuxing-quan",171);
   map_skill("unarmed","wuxing-quan");
   map_skill("parry","wuxing-quan");
   map_skill("dodge","baguazhen");
   set("max_force",1600);
   set("max_mana",2000);
   set("mana",2000);
   set("force",1600);
   set("mana_factor",80);
   set("force_factor",70);
   set("max_kee",2000);
   set("max_sen",2400);
   set("combat_exp",1400000);
   set("daoheng",800000);
   setup();
   carry_object("/d/obj/cloth/jinpao")->wear();
}
