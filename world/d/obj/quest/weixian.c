//Cracked by Roath
// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
inherit ITEM;
#include <task.h>
void create()
{
    set_name("ζ����֤", ({ "weixian" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "��");
            set("material", "cloth");
            set("long", "���ǳ�͢���͵�һ���������������֤��\n");
            set("owner_name", "��ڸ�");
          set("owner_id", "wan koufu");
          }

    setup();
}
