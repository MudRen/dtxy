//Cracked by Roath
inherit ITEM;

void create()
{
        set_name("���С��", ({ "che"}) );
        set_weight(10000000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
		set("long", "һ������ľС����\n");
                set("unit", "��");
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
                return notify_fail("��Ҫ��ʲô��\n");
        if( present("honghai er",where) )
        	return notify_fail("�캢��������һ��������ס�֣�\n");
	hong = new("/d/qujing/kusong/npc/hong");
        hong->move(where);
	tell_object(ob,"�캢��������һ��������ס�֡�\n"); 
        hong->kill_ob(ob);
        ob->kill_ob(hong);
        return 1;
}