//created by vikee
//2000.10
//huobing.c

#include <ansi.h>
inherit NPC;


void create()
{
   set_name("�����", ({ "huo bing","bing"}) );
   set("race", "����");
   set("age", 500);
   set("long", "̫���Ͼ��Ļ����.\n");
   
   set("str", 40);
   set("per", 400);
   set("cor", 26);   
   set("combat_exp",100000);
   set("daoxing",1500000);
   set("max_force",800);
   set("force",800);
   set("max_mana",2000);
   set("mana",2000);
   set("max_kee",800);
   set("max_sen",800);
   set("attitude", "aggressive");
   set_skill("dodge",140);
   set_skill("dragonstep",40);
   set_skill("huoyun-qiang",180);
   set_skill("spear",180);
   map_skill("spear","huoyun-qiang");
   map_skill("parry","huoyun-qiang");
   map_skill("dodge","dragonstep");
   set("limbs", ({ "ͷ", "����", "��", "��",}) ); 
   setup();
}

void die()
{
            if( environment() ) 
        message("sound", ""HIY"�������ʧ�ڻ�֮�С�"NOR"\n", environment());        
                destruct(this_object());
}


