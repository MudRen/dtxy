//created by vikee
//2000.10

#include <ansi.h>
inherit NPC;

void create()
{
   set_name("��ѻ", ({ "huo ya","ya","huoya" }) );
   set("race", "Ұ��");
   set("age", 500);
   set("long", "̫���Ͼ��Ļ����֮��ѻ.\n");   
   set("str", 40);
   set("per", 400);
   set("cor", 26);   
   set("combat_exp",500000);
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
   set_skill("dragonfight",80);
   set_skill("parry",180);
   set_skill("unarmed",180);
   map_skill("unarmed","dragonfight");
   map_skill("parry","dragonfight");
   map_skill("dodge","dragonstep");
   set("limbs", ({ "ͷ��", "����", "��צ", "β��","���"}) );   
   setup();
   set("chat_msg_combat", ({
                (: cast_spell, "zhenhuo" :),

   }) );

}


void die()
{
            if( environment() ) 
        message("sound", ""HIY"��ѻ��ʧ�ڻ��֮�С�"NOR"\n", environment());        
                destruct(this_object());
}

