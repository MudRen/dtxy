#include <ansi.h>

inherit ITEM;
int do_open(string arg);
void create()
{
  set_name(HIR "��������" NOR,({"gift"}));
  set("long","����һ�������������Ŵ�("+HIR+"open"+NOR+")��������");
  set("unit","��");
  set("value", 0);
  setup();
}

void init()
{
   if (!wizardp(this_player())) {
    set("no_get","��������ò�������\n");
    set("no_give","��ô���Ķ��������������ˣ�\n");
    set("no_drop","��ô����Ķ��������˶��ϧѽ��\n");
    set("no_sell","�ⶫ����������\n");
   }
    if(this_player()==environment())
  add_action("do_open", "open");
}

int do_open(string arg)
{
  object yudi;
  object me=this_player();
  if (!arg && arg!="liwu") return notify_fail("��Ҫ��ʲô?\n");
  if (me->query("newbie_liwu")) return notify_fail("���Ѿ��ù������ˣ���ô����Ҫ��\n");
  message_vision(HIG"$N�����������Ĵ򿪣�һ����â���������$N�����â��ס��$N���û������������!\n" NOR,me);
  
  me->add("potential",5000);  //the reward just is a example ,you can modify it as your wish. :P
  me->add("combat_exp",10000); //vikee 10/5/2000
  tell_object(me,HIW"�㱻�����ˣ�\n" +
  chinese_number(10000) + "����ѧ\n"+        
  chinese_number(5000) + "��Ǳ��\n" NOR);
  me->set("newbie_liwu",1);
  yudi = new("/d/dntg/sky/npc/yuhuang.c");
  yudi->command_function("chat ��˵һ������"+me->name()+"���ˣ��õ������������ʼ��������������...\n");
  destruct(yudi);
  destruct(this_object());
  return 1;
}

