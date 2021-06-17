
#include <ansi.h>
#include <dbase.h>
#include <armor.h>

inherit ITEM;

void create()
{
  set_name(HIM "��"+ HIR "ɫ" + HIC "��"NOR, ({ "bianse long","long"})); 
  set_weight(100);
  set("long","һֻ�ɰ����������棬Ҳ�б�ɫ������ô���ɵ�С�����ϲ��������(kan).\n");
  set("unit", "ֻ");
  set("value",100);
  setup();
}

int init ()
{
  remove_call_out ("start_jump");
  call_out ("start_jump",20+random(10));
  add_action ("do_get", "get");
  add_action ("do_look", "kan");
  return 1;
}

int do_get (string arg)
{
  object who = this_player();
  object bslong = this_object();

  if (arg != "bianse long" && arg != "long" && arg != "all")
    return 0;

  message_vision("$N�����ȥ׽$n��$nһ��β�ʹ�$N���������ˡ�\n",who,bslong);
  return 1;
}


int start_jump ()
{
  object bslong = this_object();
  string str = bslong->query("name")+"����������ֻСצ���ر�ɰ���\n";
  tell_room (environment(bslong),str);
  call_out("do_jump",5+random(5));
  return 1;
}

int do_jump ()
{
  object bslong = this_object();
  string *msgs = ({
    "ವ�һ����$NѸ�ٴ��˼�����\n",
    "$NŤ��Ťβ�͡�\n",
    "$NǱ��������\n",
    "$N��ͷ������������\n",
    "$N����һԾ��ҧס��һֻ���ӡ�\n",
    "$N���˶���\n",
  });
  string str;

  if (random(4) == 0)
  {
    call_out("jump_back",4);
    return 1;
  }

  str = replace_string (msgs[random(sizeof(msgs))],
                        "$N",bslong->query("name"));
  tell_room (environment(bslong),str);
  call_out("do_jump",3+random(15));
  return 1;
}

int jump_back ()
{
  object bslong = this_object();
  string str = bslong->query("name")+"��Ȼƾ����ʧ�ˡ�\n";
  tell_room (environment(bslong),str);
  destruct (bslong);
  return 1;
}

int do_look (string arg)
{
  object who = this_player();
  object bslong = this_object();

  if (arg != "bianse long" && arg != "long" && arg != "all")
    return notify_fail("��Ҫ��ʲô��\n");
        if(!who->query("m_success/��ɫ��")){
  message_vision("$N��ϸ�ؿ���$n������һ����⣬���������ʲô��\n",who,bslong);
  who->set("m_success/��ɫ��",1);
                return 1;
                }
  return 1;
}
