#include <ansi.h>
inherit ITEM;
void create()
{
  set_name("���Է�", ({"bagua fu", "fu",}));
  set_weight(100);
  set("unit", "��");
  set("value", 0);
  setup();
}
void init()
{
  object me = this_object();
  object who = this_player();
  object where = environment();
  add_action("do_direct","direct");
  if (! me->query("my_owner") &&
      interactive (who))
    me->set("my_owner",who->query("id"));
   
     if (userp(where))
  {
    if (me->query("owned"))
    {
      if (me->query("owned")!=where->query("id"))
      {
        call_out("destruct_me",1,where,me);
      }
    }
    else
    {
      me->set("owned",where->query("id"));
    }
  }
    
}

void destruct_me(object where, object me)
{
  message_vision("ǧ��ֹ�����������$n���ž��ܣ���׷��\n",where,me);
  destruct (me);
}


int do_direct (string arg)
{
  object me = this_player();
  
  if (!arg) return notify_fail("�÷���direct <direction>\n");
  write ("��������ڰ��Է���д�� "HIR+arg+ NOR" ��\n");
  set("dir",arg);
  return 1;
}
