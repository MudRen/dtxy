
#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIG"����"NOR, ({ "yao qin", "qin" }) );
	set("long", "����һ�ѹ�ɫ��������١�\n");
	set_weight(3000);
	set("unit", "��");
	setup();
}

string long()
{
	object target;
	
	if(this_player()!=query("master"))
		return "����һ�ѹ�ɫ��������١�\n";
	if(objectp(target=query("target")))
		return sprintf("����һ�Ѻ�������͸�%s(%s)�����١�\n"
			, HIM+target->name(1)+NOR,
			capitalize(target->query("id")));
	return "����һ�ѹ�ɫ��������١�\n";
}
