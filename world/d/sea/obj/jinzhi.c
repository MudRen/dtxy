#include <ansi.h> 

inherit ITEM;

void create()
{
        set_name(HIY"��ּ"NOR, ({"paper"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long",
HIY"                        ��   ּ                        ����\n"
"\n"
"         �������������ڴ��ճ�ʱ���ƣ���ʱ���ף���ʱ���꣬δ\n"
"     ʱ���㣬������ˮ������������ʮ�˵㣮��������        \n"
"\n"
"                                             �����������´�\n"NOR);
				set("material", "paper");
		}
  setup();
}
