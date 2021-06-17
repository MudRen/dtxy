// qiannengdan_xiao.c СǱ�ܵ�

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
        set_name(HIG "СǱ�ܵ�" NOR, ({"qianneng dan"}));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ��СǱ�ܵ�����˵�����������Ǳ��10��㡣(chew qianneng dan)\n");
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
        message_vision(HIG "\n$N����һ��СǱ�ܵ���Ǳ��������10���!\n" NOR, player);
        player->add("potential", 100000);
        player->save();
        log_file("player_reward", "[" + ctime(time()) + "] " + player->query("name") + "(" + player->query("id")
                 + ")" + "����һ��СǱ�ܵ���Ǳ��������10���!\n" );
        player->command("rumor " + player->query("name") + "����һ��СǱ�ܵ���Ǳ��������10���!\n" );
        destruct(this_object());
        return 1;
}

