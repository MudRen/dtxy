#include <ansi.h>
// creat by canoe 
// �����еĳͷ�
inherit NPC;
void create()
{
  set_name("��ͷ��", ({"caotou shen","shen"}));
  set("gender", "����");
  set("age", 20+random(20));
  set("con", 20);
  set("cor", 20);
  set("int", 20);
  set("per", 20);
  set("long", "����ר�����԰�ֵĲ�ͷ���е�һ����\n");
  set("attitude", "peaceful");
  set("combat_exp", 30000);
   set_skill("dodge", 25+random(30));
    set_skill("unarmed", 25+random(30));
    set_skill("parry", 25+random(30));
    set("max_gin", 300);
    set("max_kee", 300);
    set("max_sen", 300);
  set("force", 200);
  set("max_force", 100);
    set("force_factor", 30);
  set("mana", 200);
  set("max_mana", 100);
  set("mana_factor", 10);
  set_weight(300000);
  setup();

}
void init()
{
call_out("dest", 120);
}

int dest()
{
remove_call_out("dest");
message_vision(HIB"$N���˿���ĭ˵��:���̵�,�����ҿ�����!ת������ݴԡ�\n"NOR,this_object());
destruct (this_object());
}
void die ()
{
        object me = this_object();
        message_vision ("\n$Nವ�һ��,�ӻ�������......\n",me);
        destruct (me);
        return ;
  
}


void unconcious()
{
   die();
 }

