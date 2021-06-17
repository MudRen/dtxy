// qiannengdan_xiao.c 小潜能丹

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
        set_name(HIG "小潜能丹" NOR, ({"qianneng dan"}));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "粒");
                set("long", "一粒小潜能丹，据说嚼后可以增加潜能10万点。(chew qianneng dan)\n");
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
        message_vision(HIG "\n$N吃下一粒小潜能丹，潜能增加了10万点!\n" NOR, player);
        player->add("potential", 100000);
        player->save();
        log_file("player_reward", "[" + ctime(time()) + "] " + player->query("name") + "(" + player->query("id")
                 + ")" + "吃下一粒小潜能丹，潜能增加了10万点!\n" );
        player->command("rumor " + player->query("name") + "吃下一粒小潜能丹，潜能增加了10万点!\n" );
        destruct(this_object());
        return 1;
}

