#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIY"�Ͻ�������"NOR, ({"zijin hu"}));
	set_weight(100);
	if(clonep())
    		set_default_object(__FILE__);
  	else {

        set("long","һ��÷������Ͻ�����ǳ����֡���˵���н�����ħ֮�ܡ�\n");
        set("unit", "��");
        set("value", 0);
	set("no_put",1);
	set("no_sell",1);
	set("canoetask",1);
	}
	setup();
}
void init ()
{
  object me = this_object();
  object who = this_player();
  object where = environment();
  if (! me->query("my_owner") &&
      interactive (who))
    me->set("my_owner",who->query("id"));
   
  if (userp(where))
  {
    if (me->query("owned"))
    {
      if (me->query("owned")!=where->query("id"))
      {
        call_out("destruct_me",1,me);
      }
    }
    else
    {
      me->set("owned",where->query("id"));
    }
  }
    
}

void destruct_me(object me)
{
  destruct (me);
}