// danlu.c

#include <ansi.h>;
inherit ITEM;

void create()
{
	set_name(HIY"ͭ��¯"NOR, ({"danlu", "lu"}));
	set_weight(100000000000000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ����ͭ���ĵ�¯���̵��е������޷��ӽ���\n");
		set("unit", "��");
                     set("no_get","���Ǵ���ʿ�ɣ����Ҳ����������");
		set("value", 2000);
	}
}

