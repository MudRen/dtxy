//created by vikee
//2000.10

#include <ansi.h>
inherit NPC;

void create()
{
   set_name("����", ({ "huo ma","ma","horse" }) );
   set("race", "Ұ��");
   set("age", 500);
   set("long", "̫���Ͼ��Ļ����֮����.\n");
   
   set("str", 40);
   set("per", 400);
   set("cor", 26);   
   set("combat_exp",1355000);
   set("daoheng",955000);
   set("max_force",1550);
   set("force",2000);
   set("max_mana",1800);
   set("mana",2000);
   set("max_kee",1600);
   set("max_sen",1800);
   set("attitude", "aggressive");
   set_skill("dodge",140);
   set_skill("dragonstep",40);
   set_skill("dragonfight",80);
   set_skill("unarmed",180);
   set_skill("spells",150);
   set_skill("taiyi",150);
   map_skill("spells","taiyi");
   map_skill("unarmed","dragonfight");
   map_skill("parry","dragonfight");
   map_skill("dodge","dragonstep");
   set("limbs", ({ "ͷ��", "����", "��", "β��",}) );
   set("verbs", ({ "bite", "claw" }) );
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: cast_spell, "zhenhuo" :),

        }) );


   setup();

}

void die()
{
            if( environment() ) 
        message("sound", ""HIY"������ʧ�ڻ��֮�С�"NOR"\n", environment());        
                destruct(this_object());
}

