// poem.c

inherit ITEM;

void init();
int do_read();

void create()
{
        set_name("��", ({"xin","xin han"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
	set("long",
	"����������һЩ��ۣ�\n");
        set("value", 500);   
        }
}

