
#include <ansi.h>

inherit ITEM;

int do_eat(string);
void init();

void init()
{
	if(this_player()==environment())
	  add_action("do_eat", "eat");
}

void create()
{
  set_name( GRN "�϶�����" NOR , ({"change shoushen", "dan"}));
  set_weight(90);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "��");
    set("long", "һ����ʵ����裬��΢���ŵ�Щ������������֮�˾�����ϧ�ؽ�Ѱ��, ���Լ���, \n�����������. �������ಡ�ķ���������ױ���\n");
    set("value", 2000000);
    set("drug_type", "��ҩ");
    set("special_effects", "��һ������������һ. �����ǵ�quit");
  }
  setup();
}

int do_eat(string arg)
{
  object me = this_player();
  if (arg!="dan" && arg!="change shoushen")	return 0;

  if (me->query("str") <= 10) {
	  tell_object(me, "���Ѿ���ô����, ����϶��������ǲ�Ҫ�ٳ��˰�.\n");
	  return 1;
  }
  me->add("str", -1);
  message_vision(HIG "$N��������һ���϶������������У�һʱ�����������ֻ��$N��������һƬ������֬����������Ҳϸ���ˣ�\n" NOR, me);
  log_file("eat_dan", me->query("name") + "(" + me->query("id") + ")����һ���϶�����, str��Ϊ" + me->query("str") +"\n" );
  destruct(this_object());
  return 1;
}

