// bulkjinchuang.c ��ͥװ��ҩ

inherit COMBINED_ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("��ͥװ��ҩ", ({"bulk jinchuang yao", "yao", "jinchuang"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
             set("base_unit","��");
        set("unit","Щ");
                set("long", "����һ����ͥװ����ʮ������˵Ľ�ҩ����һ����10��ɢװ��\n");
                set("value", 5000);
				set("drug_type", "��ҩ");
        }
   set_amount(1);
        setup();
}

int do_eat(string arg)
{
        if (!id(arg))
                return notify_fail("��Ҫ��ʲôҩ��\n");

        else if (this_player()->query("eff_kee") ==
            this_player()->query("max_kee"))
                 {write("�����ڲ���Ҫ�ü�ͥװ��ҩ��\n");
                  return 1;
                 }
        else {
                this_player()->receive_curing("kee", 1000);
                message_vision("$N����һ����ͥװ��ҩ����ɫ�������ö��ˡ�\n",this_player());
 if (query_amount()>1)
add_amount(-1);
else destruct(this_object());
                return 1;
              }
}



