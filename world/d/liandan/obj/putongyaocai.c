// fake-tao.c ⨺��Ҹ�

#include <ansi.h>

inherit ITEM;

void init()
{
object me = this_object();
  object who = this_player();
  object where = environment();
  if (!wizardp(this_player())) {
set("no_get","������һ��"+this_object()->query("name")+"��ָ�们�䣡\n");
    set("no_give","��ô����ҩ�����������ˣ�\n");
    set("no_drop","��ô�����ҩ�����˶��ϧѽ��\n");
    set("no_sell","��������֪��"+this_object()->query("name")+"�ļ�ֵ�������Լ����Űɡ�\n");
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
call_out("destroy_me",120,where,me);
  }                                                            

}
void destruct_me(object where, object me)
{
  message_vision("ǧ��ֹ�����������$n���ž���,��׷!\n",where,me);
  destruct (me);
}

void create()
{
  set_name(YEL"��ͨҩ��"NOR, ({"putong yaocai","yaocai"}));
  set_weight(20);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "��");
    set("long", "һ����ͨҩ�ģ�������ɵ�ҩ��ǿ�����������ٵĹ�Ч��\n");
    set("canoe",1); // ��ݼ���,��ֹ��ҩ��
    set("value", 0);
	set("drug_type", "��Ʒ");
  }
  
  setup();
}
