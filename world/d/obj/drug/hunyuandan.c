// hunyuandan.c ��Ԫ��

inherit COMBINED_ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("��Ԫ��", ({"hunyuan dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "Щ");
                set("base_unit", "��");
                set("long", "һ���Դ�������ҩ�裮\n");
                set("value", 100);
				set("drug_type", "��ҩ");
        }
     set_amount(1);
        setup();
}

int do_eat(string arg)
{
        if (!id(arg))
                return notify_fail("��Ҫ��ʲôҩ��\n");
        if ((int)this_player()->query("eff_sen") ==
            (int)this_player()->query("max_sen")) {
                write("�����ڲ���Ҫ�û�Ԫ����\n");
                return 1;
			}
        else {
                this_player()->receive_curing("sen", 100);
                message_vision("$N����һ�Ż�Ԫ������ɫ�������ö��ˣ�\n",
this_player());
	if (query_amount()>1)
         add_amount(-1);
	else destruct(this_object());
                return 1;
        }
}

