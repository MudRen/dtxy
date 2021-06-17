// qiannengdan_da.c ��Ǳ�ܵ�

#include <ansi.h>

inherit ITEM;

int do_eat(string);
void init();

void init()
{
        add_action("do_chew", "chew");
}

void create()
{
        set_name(HIG "��Ǳ�ܵ�" NOR, ({"qianneng dan"}));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ����Ǳ�ܵ�����˵�����������Ǳ��50��㡣(chew qianneng dan)\n");
                set("value", 0);
        }
        setup();
}

int do_chew(string arg)
{
       string attr;
       object player = this_player();

        if (arg != "qianneng dan")
                return notify_fail("chew qianneng dan\n");
        message_vision(HIG "\n$N����һ����Ǳ�ܵ���Ǳ��������50���!\n" NOR, player);
        player->add("potential", 500000);
        player->save();
        log_file("player_reward", "[" + ctime(time()) + "] " + player->query("name") + "(" + player->query("id")
                 + ")" + "����һ����Ǳ�ܵ���Ǳ��������50���!\n" );
        player->command("rumor " + player->query("name") + "����һ����Ǳ�ܵ���Ǳ��������50���!\n" );
        destruct(this_object());
        return 1;
}

