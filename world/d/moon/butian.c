// ����̨
// writted by mind 2001/2
inherit ROOM;
void create()
{
        set("short", "Ů洲���̨");
        set("long", @LONG
���������ؼ���һ����ʵ��ұڡ�����������һ����һ�����ι�״ɫ�ʰ�쵵�
������ʯ����Щ����ʯ��stone����������һ����ѩɫӳ����������⡣���
���ɺõ����֮����������ȡ������¾�������֤������
LONG
        );
        set("butian-force_practice",1);
set("objects", ([ /* sizeof() == 2 */
]));
        set("exits", ([ /* sizeof() == 1 */
  "down" : __DIR__"fabao-room",
]));
        set("item_desc", ([
                "stone": "������һ���ʯͷ��ϸϸ�ѷ�֮���ж����������⡣
���ƺ�Ҳ�����������������ˣ�qiao����Զ��ʱ����Ů�ʯ��\n"
        ]) );
        
        setup();
}
void init()
{
add_action("do_qiao","qiao");
}
int do_qiao(string arg)
{
object me,weapon;
if(!arg ) return notify_fail("��Ҫ��ʲô������Ů�ʯ��\n");
me=this_player();
if(!(weapon = present(arg,me))) return notify_fail("�������ƺ�û������������\n");
if(!weapon->query("weapon_prop")) return notify_fail(weapon->name()+"�ƺ�������һ��������\n");
if(!weapon->query("equipped")) return notify_fail("�㲢û�н�"+weapon->name()+"�������С�\n");
if(weapon->query("no_give") || weapon->is_newitem() || weapon->query("no_break")) return notify_fail("��ô����Ķ���������ʯͷ��̫�˷��˰ɣ�\n");
message_vision("$N�þ�ȫ���������е�"+weapon->name()+"�����ѷ���ʹ��һ�ˡ�\n",me);
weapon->unequip();
weapon->set("weapon_prop",0);
weapon->save();
me->reset_action();
message_vision("ֻ������������һ����$N���е�"+weapon->name()+"Ӧ�����ϣ�\n",me);
weapon->set("name","�ϵ���" + weapon->query("name"));
weapon->set("value",0);
weapon->set("no_drop",0);
if(random(10))
tell_object(this_object(),"������һ���ʯͷ�ƺ���Щ�ɶ����ѷ�����ˣ�\n");
else
{
tell_object(this_object(),"һ��СС�����ʯ�Ӵ��ѷ��е��˳�����\n");
weapon = new(__DIR__"obj/butian_stone");
weapon->move(this_object());
}
if(!me->query("m_success/����ʯ"))
        {
                me->set("m_success/����ʯ",1);
                me->add("potential",500+random(500));
        }
me->start_busy(2);
return 1;
}

