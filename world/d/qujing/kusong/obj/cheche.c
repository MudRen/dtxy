//Cracked by Roath

inherit ITEM;


void create()
{
        set_name("���С��", ({ "che"}) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("value",0);
                set("unit", "��");
                set("no_get",1);
                set("long","һ���ܲ�Ѱ���ĳ���\n");
        }
}
