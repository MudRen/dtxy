#include <ansi.h>
inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
   set_name(HIY"����ɿ���"NOR+"", ({"chocolate", "ice", "qiaokeli"}));
                  set("unit", "��");
                  set("long", MAG"����ɿ�����ֻ������ˡ�\n"NOR);
                set("value", 0);
                set("drug_type", "��ʳ");
        setup();
}

int do_eat(string arg)
{
object me = this_player();
        if (!id(arg))
                return notify_fail("��Ҫ��ʲô��\n");
message_vision(MAG"$Nһ�ڽ��ɿ��������¶ǣ���ʱ�ľ�������������������������\n"NOR, this_player())
;
me->set("water",1000);
me->set("food",1000);
        destruct(this_object());
        return 1;
        }

