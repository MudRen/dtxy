// By canoe 2001.03.25
#include <ansi.h>

inherit NPC;
int handle_kill(object me);
 
void create()
{
        set_name("����Ȯ", ({ "xiaotian quan","quan","dog" }) );
        set("long", 
                "��꯵�����Ȯ��\n"
        );
        set("race", "Ұ��");
        set("title","�����ɷ");
        set("rank_info/respect", "�ɰ���С����");
        set("rank_info/rude", "����");
		set("age", 400);
        set("str", 25);
        set("int", 20);
        set("per", 15+random(10));
        set("combat_exp", 270000);
        //set("daoxing", 50000);
        set("attitude", "friendly");
        set("max_kee", 2000);
        set("max_sen", 2000);
        set("force",2000);
        set("max_force",2020);
        set("force_factor", 100);
        set("mana", 200);
        set("max_mana", 200);
        set("mana_factor", 20);
        set_skill("dodge",360);
   set_skill("dragonstep",360);
   set_skill("dragonfight",360);
   set_skill("unarmed",360);
   map_skill("unarmed","dragonfight");
   map_skill("parry","dragonfight");
   map_skill("dodge","dragonstep");
   set("limbs", ({ "ͷ��", "����", "��", "β��",}) );
   set("verbs", ({ "bite", "claw" }) );
      setup();
 }
 
/*void heart_beat() {
       
   set("eff_kee", 2000);
   set("eff_sen", 2000);
   set("kee",2000);
   set("sen",2000);
   set("force",2000);
       
   ::heart_beat();
}
*/
void init()
{
	add_action("do_kill", "kill");
}

void die()
{
   object ob,who;
   ob=this_object();
 message("sound", "\n\nХ��Ȯ�������ˣ����м�������β����÷ɽ��ȥ��\n\n", environment());
//  message_vision(HIY"\n\nХ��Ȯ�������ˣ����м�������β����÷ɽ��ȥ��\n\n"NOR,who);

   destruct(ob);
   return;
}

int do_kill(string arg)
{
    if(!id(arg)) return 0;
    handle_kill(this_player());
    return 0;
}
int handle_kill(object me)
{
    if (me->query("fangcun/panlong_nowaypansi"))
  {
	  set_skill("dodge",200);
   set_skill("dragonstep",200);
   set_skill("dragonfight",200);
   set_skill("unarmed",200);

  }
    command("kill "+me->query("id"));
}

