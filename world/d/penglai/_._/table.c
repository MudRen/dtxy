//created by vikee
//2000.11

#include <ansi.h>
inherit ITEM;
int get_gift(string arg);
void create()
{
  set_name(HIY"����̨" NOR ,({"gift table","table"}));
  set("long","���Ǵ���������ʦΪ�˽���������������̨����ҿ�����������(take)����(gift)��");
  set("unit", "��");
  set("value", 1000000000000);
}
void init()
{
  if (!wizardp(this_player())) 
   set("no_get","��������ò�������\n");
  add_action("get_gift","take");
}
int get_gift(string arg)
{
  object me = this_player();
  object lw;
  if (arg!="gift")      return 0;
  if (me->query("newbie_gift")) return notify_fail("���Ѿ��ù�������,��̫̰��Ӵ��\n");
  message_vision("$N������̨������һ�����\n" NOR, me);
  lw=new("/u/vikee/gift");
  lw->move(me);
  me->set("newbie_gift",1);
  return 1;
}
