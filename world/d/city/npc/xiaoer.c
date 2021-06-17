//"panshi dan": "/u/take/panshidan",
inherit F_VENDOR_SALE;
int random_go(object me, string* dirs);

// #include <norumor.c>
void create()
{
       reload("xiaoer");
       set_name("��С��", ({"xiao er","xiaoer","xiao","waiter","er"}));
       set("shop_id",({"waiter","xiaoer","xiao","er"}));
       set("shop_title","��С��");
       set("gender", "����");
        set("combat_exp", 1000);
       set("age", 26);
       set("per", 14);
       set("attitude", "friendly");
       set("shen_type", 1);
       set_skill("unarmed", 10);
       set("max_price",20);
        set("vendor_goods", ([
                "jiudai": "/d/moon/obj/jiudai",
                "gourou": "/d/ourhome/obj/gourou",
              "jinpai" : "/d/obj/misc/tiaozhanpai",
"tu": "/d/city/obj/tu",
               "xmap": "/d/obj/misc/xueshan-map",
               "pmap": "/d/penglai/npc/obj/ditu",
               "pillow": "/d/obj/misc/pillow",
                "jitui": "/d/ourhome/obj/jitui",
               "ball": "/d/obj/misc/crystalball",
                "huasheng": "/d/ourhome/obj/huasheng",
                "zhinan": "/d/obj/misc/xiaqi-zhinan",
             "zhengsu":"/d/qujing/chechi/obj/zhengsu",
                "huicheng":"/d/city/obj/huicheng",
                "mastercard":"/d/obj/master_card",
                "yinsuo":"/d/pansi/obj/yinsuo.c",
                "qin":"/d/pansi/obj/qin.c",
                  "xieyao":"/u/yekai/other/xieyao.c",
        ]) );

        if( clonep() ) CHANNEL_D->register_relay_channel("rumor");
       setup();

       carry_object("/d/obj/cloth/linen")->wear();
carry_object("/d/wiz/npc/caishen")->wear();
       add_money("silver", 1);
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_vendor_list", "list");
}

void greeting(object ob)
{
        if( !ob || !visible(ob) || environment(ob) != environment() ) return;
        switch( random(3) ) {  // 1/3 chance to greet.
                case 0:
                        say( name()+"Ц�����˵������λ" +RANK_D->query_respect(ob)
                                + "������ЪЪ�ţ������Ѱɡ�\n");
                        break;
        }
}

void clear_room()
{
        string *place1 =
        ({"/d/city/zhuque-s1","/d/city/center","/d/city/xuanwu-n1",
        "/d/city/baihu-w1","/d/city/qinglong-e1"});

        string room;
        int race, obj,i;
        object *inv;
        race = 0;
        obj = 0;
        if(environment(this_object())){
        inv = all_inventory(environment(this_object()));
      
        say(name()+"��Ǹ��˵������С����ɨ����λ�͹�ԭ���������\n");
      

        if ( sizeof(inv) <= 0 ) return ;

        for (i = 0;i <sizeof(inv);i++)
        {
                if(inv[i]->query("race")=="Ұ��")
                {
                        room = place1[random(5)];
                        say(inv[i]->query("name")+"��"+name()+"��ɨ����˳�ȥ��\n");
                        inv[i]->set_temp("no_return",0);
                        inv[i]->set_temp("rider",0);
                        inv[i]->move(room);
                        tell_room(environment(inv[i]), inv[i]->query("name")+"��"+name()+"�ӿ�ջ���˳�����\n");
                        race++;
                }
                else if(!inv[i]->is_character()&&!inv[i]->query("board_id")) 
                {obj++; destruct(inv[i]);}
                if(inv[i]->query_temp("ridee"))
                {

                        inv[i]->set_temp("ridee",0);
                        inv[i]->add_temp("apply/dodge",-inv[i]->query_temp("ride/dodge"));
                        inv[i]->set_temp("ride/dodge",0);

                 }
        }
      if(race+obj==0) say(name()+"���������ɨ�˰��죬����ûʲô���Դ�ɨ�ģ�����������˹�̨��\n");
      CHANNEL_D->do_channel(this_object(),"sys","��������"+chinese_number(race)+"ֻ����������"+chinese_number(obj)+"����\n");
     }
      remove_call_out("clear_room");
      call_out("clear_room",300);
}
int accept_object(object who, object ob)
{
   if (ob->query("money_id") && ob->value() >= 300) 
   {
     tell_object(who, "С��һ������˵������л���ϣ��͹�����¥ЪϢ��\n");
     who->set_temp("rent_paid",1);
     return 1;
   }
   return 0;
}
