// randomshuxindan.c 随机属性丹

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
        set_name(HIG "随机属性丹" NOR, ({"random shuxing dan"}));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "粒");
                set("long", "一粒随机属性丹，据说嚼后可以随机增加某一属性10点。(chew random shuxing dan)\n");
                set("value", 0);
        }
        setup();
}

int do_chew(string arg)
{
       string attr;
       object player = this_player();

       if ( !arg || arg != "random shuxing dan" )
        		return notify_fail("你要吃什么?\n");
        attr = gift[random(sizeof(gift))];
        message_vision(HIG "\n$N吃下一粒随机属性丹，" + attr + "增加了10点!\n" NOR, player);
        player->add(attr, 10);
        player->save();
        log_file("player_reward", "[" + ctime(time()) + "] " + player->query("name") + "(" + player->query("id")
                 + ")" + "吃下一粒随机属性丹，" + attr + "增加了10点到" + player->query(attr) + "!\n" );
        player->command("rumor " + player->query("name") + "吃下一粒随机属性丹，" + attr + "增加了10点" );
        destruct(this_object());
        return 1;
}

