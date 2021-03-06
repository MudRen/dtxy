// shuxindan.c 属性丹

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
        set_name(HIG "属性丹" NOR, ({"shuxing dan"}));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "粒");
                set("long", "一粒属性丹，据说嚼后可以增加某一指定属性10点。(chew shuxing dan for int|kar...)\n");
                set("value", 0);
        }
        setup();
}

int validate_gift_arg(string arg) {
	if (arg != "int" && arg != "str" && arg != "con" && arg != "spi" && arg != "per" && arg != "kar"
	     && arg != "cps" && arg != "cor")
		return 0;
	else
		return 1;
}

int do_chew(string arg)
{
       string attr;
       object player = this_player();

        if (sscanf(arg, "shuxing dan for %s", attr) != 1)
                return notify_fail("chew shuxing dan for int|kar...\n");
        if ( !attr || !validate_gift_arg(attr) )
        		return notify_fail("chew shuxing dan for int|kar...\n");
        message_vision(HIG "\n$N吃下一粒属性丹，" + attr + "增加了10点!\n" NOR, player);
        player->add(attr, 10);
        player->save();
        log_file("player_reward", "[" + ctime(time()) + "] " + player->query("name") + "(" + player->query("id")
                 + ")" + "吃下一粒属性丹，" + attr + "增加了10点到" + player->query(attr) + "!\n" );
        player->command("rumor " + player->query("name") + "吃下一粒属性丹，" + attr + "增加了10点" );
        destruct(this_object());
        return 1;
}

