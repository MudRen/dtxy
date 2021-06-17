// zaoshen.c

inherit F_VENDOR_SALE;

int do_cookie();

void create()
{
        set_name("����ү", ({"zao wangye","wangye"}));
        set("title", "�ϳǿ�ջ");
        set("gender", "����" );
        set("age", 16);
        set("long", "һ�������������ֵ�����ү����������Ц��\n");
        set("combat_exp", 2000);
        set("attitude", "friendly");
	set("vendor_goods", ([
//      		"renshen guo": "/d/obj/drug/renshen-guo",
		"parry book": "/d/obj/book/parrybook2.c",
		"force book": "/d/obj/book/forcebook2.c",
		]) );
        set("inquiry", ([
// "�±�" : (: do_cookie :),
//"cookie" : (: do_cookie :),
        ]) );

        setup();

}
void init()
{
::init();
        add_action("do_yao", "yao");
        add_action("do_vendor_list", "list");
}

int do_yao(string arg)
{
        object m,mm,me;
        message_vision("$N��ƤЦ����������ү�ʵ�:���������ģ���û�м�����ѽ?\n", this_player());
	me=this_player();
	if (!userp(me))
	 {
	   message_vision("����ү����һ������С����Ҳ��������?��\n",me);
	   return 1;
         }
        if ( me->query("wizgift/newbiegift") )
         return notify_fail("����үһ���ۣ������ң�\n"); 
	if ( present("lipin box",me))
	 return notify_fail("����ү̾�˿���������ô��ô̰��?\n");
        m=new("/d/obj/drug/giftbox");
        m->move(this_player());
	log_file("static/NEWBIEGIFT","["+ctime(time())+"] "+sprintf("%s(%s)������ү���õ���%s(%s)\n",
         this_player()->query("name"),this_player()->query("id"),
         m->query("name"),m->query("id")));
	message_vision("����ү��$Nһ����Ʒ��.\n", this_player());
        message_vision("����ү��$NЦ�����ú�����\n", this_player());
return 1;
}

int do_bid(string arg)
{
	if (!wizardp(this_player()))
	  return notify_fail("�㲻�������ﵱ�ϰ塣:-) \n");
 	return ::do_bid(arg);
}
int do_cookie()
{
        object m,mm,me;
        me=this_player();
        if (!userp(me))
         {
           message_vision("����ү����һ������С����Ҳ��������?��\n",me);
           return 1;
         }
        if ( me->query("wizgift/cookiegift") )
         return notify_fail("����үһ���ۣ������ң�\n");
        if ( present("yuebing box",me))
         return notify_fail("����ү̾�˿���������ô��ô̰��?\n");
	me->set("wizgift/cookiegift",1);
	me->save();
        m=new("/d/obj/drug/cookie_box");
	mm=new("/d/obj/drug/cookie");
	mm->move(m);
        mm=new("/d/obj/drug/cookie");
        mm->move(m);
        mm=new("/d/obj/drug/cookie");
        mm->move(m);
        mm=new("/d/obj/drug/cookie");
        mm->move(m);
        m->move(this_player());
   log_file("static/COOKIEGIFT","["+ctime(time())+"] "+sprintf("%s(%s)������ү���õ���%s(%s)\n",
         this_player()->query("name"),this_player()->query("id"),
         m->query("name"),m->query("id")));
        message_vision("����ү��$Nһ���±���.\n", this_player());
        message_vision("����ү��$NЦ�����úúá�\n", this_player());
	return 1;
}
