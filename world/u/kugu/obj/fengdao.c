// blade.c
//�Ϸ���µ�
#include <ansi.h>
#include <weapon.h>

inherit BLADE;

void create()
{
	set_name(HIM"��"+HIR"��"+HIW"��"NOR, ({"fengyue dao", "dao", "blade"}) );
	set_weight(6000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 500);
		set("material", "iron");
		set("long", "����һ��Ư����˫��Ϸ�µ����ഫ����������\n");
		set("wield_msg", "$N���һ��$n�������������������\n");
		set("unequip_msg", "$N����$n������ɲ�Ǽ���ʧ�ˡ�\n");
	}
	init_blade(200);
	setup();
}
int query_autoload() { return 1; }