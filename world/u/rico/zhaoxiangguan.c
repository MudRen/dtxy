inherit ROOM;

void create ()
{
        set ("short", "���������");
        set ("long", @LONG

�����������������ǰ���ĵط��ˡ�
ǽ�����ܹ��������ǵ���Ƭ����̬���졣
��Ӱʦ�����Աߣ��к��ſ��ˡ�
���������������Ѿ���Ϊ��������,ֻ�ǰ�������
���ˡ�
LONG);
      set("exits", ([ /* sizeof() == 1 */
      "southeast" : __DIR__"home",
           "east" : __DIR__"zxg-1",
]));
        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/sheyingshi" : 1]));
  set("no_clean_up", 0);
  set("no_fight", 1);
  set("no_magic", 1);



        setup();
}


void init() {
  add_action("do_borrow",({"borrow","jie"}));
}

int do_borrow(string arg) {

   object camera,me=this_player();
   camera=new("/obj/toy/camera");
   camera->move(this_player());
   message_vision("�������$Nһ���������\n",me);
   return 1;
}         

int valid_leave (object camera, string dir)
{
   camera=this_object();

        if (camera=present("camera",this_player()) && dir == "southeast") {
        return notify_fail("�㲻�ܰ���������ߣ�\n");
        tell_object(this_player(),"�㽫������ظ������롣\n");
//        destruct(camera);
        this_player()->move("/u/rico/home");
        }
    return ::valid_leave();

}
