// huanyang.c 还阳丹

#include <ansi.h>

inherit ITEM;

int do_eat(string);
void init();

void init()
{
        if (!wizardp(this_player())) {
//                set("no_get", "嘿嘿，做梦吧! \n");
                set("no_drop","这么宝贵的还阳丹，哪能乱扔! \n");
                set("no_give","这么宝贵的还阳丹，哪能给人! \n");
                set("no_sell","这么宝贵的还阳丹，哪能卖! \n");
                set("no_put","这么宝贵的还阳丹，放进口袋里面不太安全吧! \n");
        }

        add_action("do_eat", "eat");
}

void create()
{
        set_name(HIG "还阳丹" NOR, ({"huanyang dan", "dan"}));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "粒");
                set("long", "一粒还阳丹，据说有起死回生之效。\n");
                set("value", 200000000);
        }

        set("is_monitored", 1);
        setup();
}

int do_eat(string arg)
{
        object victim = this_player();

        if (!id(arg))
                return notify_fail("你要吃什么？\n");

		if (!victim->query("death"))
				return notify_fail("你又没有死过, 吃什么还阳丹？\n");

        victim->add("combat_exp", (int)victim->query("death/combat_exp_loss"));
		victim->add("potential", (int)victim->query("death/potential_loss"));
		victim->skill_death_recover();
		victim->add("daoxing",victim->query("death/dx_loss"));
		if( userp(victim) ) log_file("RECOVER", sprintf("%s(%s) Got recovered on %s, exp(%d), dx(%d), pot(%d).\n",
			victim->name(1), geteuid(victim), ctime(time()), victim->query("death/combat_exp_loss"),
			victim->query("death/dx_loss"), victim->query("death/potential_loss")) );
	    victim->delete("death");
       victim->save();
       message_vision(HIG "\n$N吃下一粒还阳丹，硬是从白无常那里逃脱，捡回了一条小命。\n\n" NOR, victim);

        destruct(this_object());
        return 1;
}

