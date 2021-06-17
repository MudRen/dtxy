// bulkjinchuang.c 家庭装金创药

inherit COMBINED_ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("家庭装金创药", ({"bulk jinchuang yao", "yao", "jinchuang"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
             set("base_unit","包");
        set("unit","些");
                set("long", "这是一包家庭装分量十足的治伤的金创药。吃一个顶10个散装的\n");
                set("value", 5000);
				set("drug_type", "良药");
        }
   set_amount(1);
        setup();
}

int do_eat(string arg)
{
        if (!id(arg))
                return notify_fail("你要吃什么药？\n");

        else if (this_player()->query("eff_kee") ==
            this_player()->query("max_kee"))
                 {write("你现在不需要用家庭装金创药。\n");
                  return 1;
                 }
        else {
                this_player()->receive_curing("kee", 1000);
                message_vision("$N吃下一包家庭装金创药，气色看起来好多了。\n",this_player());
 if (query_amount()>1)
add_amount(-1);
else destruct(this_object());
                return 1;
              }
}



