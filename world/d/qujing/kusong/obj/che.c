//Cracked by Roath
inherit ITEM;

void create()
{
        set_name("漆金小车", ({ "che"}) );
        set_weight(10000000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
		set("long", "一辆漆金红木小车。\n");
                set("unit", "辆");
        }
}

void init()
{
        add_action("do_get","get");
}
int do_get(string arg)
{
        object ob = this_player();
        object where = environment();
        object hong;

        if( ! arg || arg != "che" )
                return notify_fail("你要拿什么？\n");
        if( present("honghai er",where) )
        	return notify_fail("红孩儿对你大吼一声：给我住手！\n");
	hong = new("/d/qujing/kusong/npc/hong");
        hong->move(where);
	tell_object(ob,"红孩儿对你大吼一声：给我住手。\n"); 
        hong->kill_ob(ob);
        ob->kill_ob(hong);
        return 1;
}