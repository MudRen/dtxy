//Cracked by Roath
// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
inherit ITEM;

int do_locate(string arg);
int do_task();

void create()
{
        set_name("ˮ����", ({"shuijing qiu","qiu"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "����һ������Ѱ�Ҷ�ʧ�����ˮ���������зǷ���ħ����\n"+
                            "����(locate)�����ҵ���Ʒ�Ĵ��λ�ã�\n");
                set("unit", "��");
                set("value", 300);
        }
}

void init()
{
        object ob = this_player();

  add_action("do_locate","locate");
  add_action("do_task","task");
}

int do_task()
{
   string output;
   output="ˮ������ͻȻӳ�ֳ�һƪӬͷС�֣�\n\n"+"/adm/daemons/questd"->dyn_quest_list();
   this_player()->start_more(output);
   return 1;
}

int query_autoload() { return 1; }

int do_locate(string arg)
{
   if ( ! arg)

   return notify_fail("locate <��Ʒ>\n");
   else
   "/adm/daemons/questd"->locate_quest(this_player(),arg�Ʌw)��6o~m#�y��