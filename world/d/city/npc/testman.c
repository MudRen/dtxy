// zaoshen.c

inherit F_VENDOR_SALE;

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

        setup();

}
void init()
{
//add_action("do_yao", "yao");
        add_action("do_vendor_list", "list");
add_action("do_yao","yao");
}

int do_yao(string arg)
{
        object m,mm,me;
        message_vision("$N��ƤЦ����������ү�ʵ�:���������ģ���û�м�����ѽ?\n", this_player());
	me=this_player();
        if ( me->query("wizgift/newbiegift") )
         return notify_fail("����үһ���ۣ������ң�\n"); 
//	if ( me->query("combat_exp") < 5000 )
//	 return notify_fail("����ү˵��: С�һ����㹦��������!\n");
//
        m=new("/d/obj/drug/giftbox");
//        mm=new("/obj/money/thousand-cash");
        m->move(this_player());
//        mm->move(this_player());
	me->set("wizgift/newbiegift",1);
	log_file("static/NEWBIEGIFT","["+ctime(time())+"] "+sprintf("%s(%s)������ү���õ���%s(%s)\n",
         this_player()->query("name"),this_player()->query("id"),
         m->query("name"),m->query("id")));
	message_vision("����ү��$Nһ����Ʒ��.\n", this_player());
//        message_vision("����ү��$Nһ��һǧ������Ʊ\n",this_player()); 
        message_vision("����ү��$NЦ�����ú�����\n", this_player());
return 1;
}

int do_bid(string arg)
{
	if (!wizardp(this_player()))
	  return notify_fail("�㲻�������ﵱ�ϰ塣:-) \n");
 	return ::do_bid(arg);
}

