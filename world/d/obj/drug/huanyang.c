// huanyang.c ������

#include <ansi.h>

inherit ITEM;

int do_eat(string);
void init();

void init()
{
        if (!wizardp(this_player())) {
//                set("no_get", "�ٺ٣����ΰ�! \n");
                set("no_drop","��ô����Ļ���������������! \n");
                set("no_give","��ô����Ļ����������ܸ���! \n");
                set("no_sell","��ô����Ļ�������������! \n");
                set("no_put","��ô����Ļ��������Ž��ڴ����治̫��ȫ��! \n");
        }

        add_action("do_eat", "eat");
}

void create()
{
        set_name(HIG "������" NOR, ({"huanyang dan", "dan"}));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ������������˵����������֮Ч��\n");
                set("value", 200000000);
        }

        set("is_monitored", 1);
        setup();
}

int do_eat(string arg)
{
        object victim = this_player();

        if (!id(arg))
                return notify_fail("��Ҫ��ʲô��\n");

		if (!victim->query("death"))
				return notify_fail("����û������, ��ʲô��������\n");

        victim->add("combat_exp", (int)victim->query("death/combat_exp_loss"));
		victim->add("potential", (int)victim->query("death/potential_loss"));
		victim->skill_death_recover();
		victim->add("daoxing",victim->query("death/dx_loss"));
		if( userp(victim) ) log_file("RECOVER", sprintf("%s(%s) Got recovered on %s, exp(%d), dx(%d), pot(%d).\n",
			victim->name(1), geteuid(victim), ctime(time()), victim->query("death/combat_exp_loss"),
			victim->query("death/dx_loss"), victim->query("death/potential_loss")) );
	    victim->delete("death");
       victim->save();
       message_vision(HIG "\n$N����һ����������Ӳ�ǴӰ��޳��������ѣ������һ��С����\n\n" NOR, victim);

        destruct(this_object());
        return 1;
}

