
inherit ITEM;

void create()
{
	int i;

        set_name("�±���", ({ "cookie box","box" }) );
        set_weight(500);
        set_max_encumbrance(8000);
        if( clonep() )
          {
          seteuid(getuid());
          set_default_object(__FILE__);
          }
        else 
          {
          set("unit", "��");
          set("long", "һ���ɴ�����������վ��ʦ���������±���ף��������֣�\n");
          set("no_give", 1);
          }
}

int is_container() { return 1; }

