#include <ansi.h>

inherit ITEM;

int do_eat(string);
void init();

void init()
{
  if (!wizardp(this_player())) {
    set("no_give","��ô����ҩ�����������ˣ�\n");
    set("no_drop","��ô����ĵ�ҩ�����˶��ϧѽ��\n");
    set("no_sell","��������֪��"+this_object()->query("name")+"�ļ�ֵ�������Լ����Űɡ�\n");
  }                                    
    add_action("do_eat", "eat");
}

void create()
{
  set_name(HIW "������" NOR, ({"wuming dan","dan"}));
  set_weight(200);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "ö");
    set("long", "һö��֪����ʲô�õĵ���\n");
    set("value", 5000);
        set("drug_type", "��Ʒ");
  }

  set("is_monitored",0);
  setup();
}

int do_eat(string arg)
{
  object me = this_player();
  if (arg!="dan" && arg!="huanhun dan") return 0;

   me->add_maximum_force(500);
   me->add_maximum_mana(500);
  message_vision("$N����һ�ŵ�ҩ,����û��ʲô��Ӧ.\n");
  destruct(this_object());
  return 1;
}
