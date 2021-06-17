// by mind
#include <ansi.h>

inherit ITEM;

string *prefixs = ({
  HIR"����"NOR,
  HIG"����"NOR,
  HIY"�"NOR,
  HIC"����"NOR,
});

string *names = ({
  HIB"˫��"NOR,
  HIM"����"NOR,
  MAG"����"NOR,
});

string *suffixs = ({
  HIW"����"NOR,
  RED"����"NOR,
});

void create()
{
  set_name(prefixs[random(sizeof(prefixs))]+names[random(sizeof(names))]+
           suffixs[random(sizeof(suffixs))], ({"bian pao", "pao", "bomb"}));
  set_weight(5000);
        set("explosive",1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "�����������ʱ�򾭳�ȼ�ŵ����ڣ��е�����������ġ�\n");
        }

  setup();
}
