// randomshuxindan.c ������Ե�

#include <ansi.h>

inherit ITEM;

string *gift = ({"int", "str", "con", "spi", "per", "kar", "cps", "cor"});

void init();

void init()
{
        add_action("do_chew", "chew");
}

void create()
{
        set_name(HIG "������Ե�" NOR, ({"random shuxing dan"}));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ��������Ե�����˵��������������ĳһ����10�㡣(chew random shuxing dan)\n");
                set("value", 0);
        }
        setup();
}

int do_chew(string arg)
{
       string attr;
       object player = this_player();

       if ( !arg || arg != "random shuxing dan" )
        		return notify_fail("��Ҫ��ʲô?\n");
        attr = gift[random(sizeof(gift))];
        message_vision(HIG "\n$N����һ��������Ե���" + attr + "������10��!\n" NOR, player);
        player->add(attr, 10);
        player->save();
        log_file("player_reward", "[" + ctime(time()) + "] " + player->query("name") + "(" + player->query("id")
                 + ")" + "����һ��������Ե���" + attr + "������10�㵽" + player->query(attr) + "!\n" );
        player->command("rumor " + player->query("name") + "����һ��������Ե���" + attr + "������10��" );
        destruct(this_object());
        return 1;
}

