// poem.c

inherit ITEM;

void init();
int do_read();

void create()
{
        set_name("信", ({"xin","xin han"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "封");
	set("long",
	"信上隐隐有一些泪痕．\n");
        set("value", 500);   
        }
}

