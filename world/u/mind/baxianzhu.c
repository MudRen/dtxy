// by mind
#include <ansi.h>

inherit ITEM;

void create()
{
  set_name(RED"�οպ�ľ������"NOR, ({"baxian zhuo", "zhuo", "table"}));
  set_weight(9000);
  if( clonep() )
    set_default_object(__FILE__);
  else
  {
    set("long", "һ���οպ�ľ��������������ҵ����棱����������
    1����ѩ����
    2����������
    3��������˿
    4���������
    5�����㶬��
    6��ʱ���߲�
    7����ݮ
    8��������
    9�����з
    10����������
    11��ҰĢ��
    12�����ƺ�
    13���ɾ���
    14����������
    15������������
Ȼ��Ϳ�������(zhengzhi)��һ����Բ��ϯ��\n");
    set("material", "wood");
    set("unit", "��");
    set("value", 1200);
  }
  setup();
}

void init()
{
  if(this_player()==environment())
  add_action("do_zhengzhi","zhengzhi");
}

int do_zhengzhi()
{
int i,geng=0,jiding=0,dusi=0,zhugan=0,dongsun=0,shucai=0,caomei=0,niluo=0,pangxie=0,doufu=0,mogu=0,jiuhu=0,jiuzhong=0,fan=0,zhu=0;
object tuanyuanyanxi,me, *inv;
object geng1,jiding1,dusi1,zhugan1,dongsun1,shucai1,caomei1,niluo1,pangxie1,doufu1,mogu1,jiuhu1,jiuzhong1,fan1,zhu1;
me = this_player();

inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                {
                        if(inv[i]->query("name") == "��ѩ����") {geng = 1; geng1 = inv[i];}
                        if(inv[i]->query("name") == "��������") {jiding = 1; jiding1 = inv[i];}
                        if(inv[i]->query("name") == "������˿") {dusi = 1; dusi1 = inv[i];}
                        if(inv[i]->query("name") == "�������") {zhugan = 1;  zhugan1 = inv[i];}
                        if(inv[i]->query("name") == "���㶬��") {dongsun = 1; dongsun1 = inv[i];}
                        if(inv[i]->query("name") == "ʱ���߲�") {shucai = 1; shucai1 = inv[i];}
                        if(inv[i]->query("name") == "��ݮ") {caomei = 1; caomei1 = inv[i];}
                        
                        if(inv[i]->query("name") == "������") {niluo = 1; niluo1 = inv[i];}
                        if(inv[i]->query("name") == "��������") {doufu = 1; doufu1 = inv[i];}
                        if(inv[i]->query("name") == "���з") {pangxie = 1; pangxie1 = inv[i];}
                        if(inv[i]->query("name") == "ҰĢ��") {mogu = 1;  mogu1 = inv[i];}
                        if(inv[i]->query("name") == "���ƺ�") {jiuhu = 1; jiuhu1 = inv[i];}
                        if(inv[i]->query("name") == "�ɾ���") {jiuzhong = 1; jiuzhong1 = inv[i];}
                        if(inv[i]->query("name") == "��������") {fan = 1; fan1 = inv[i];}
                        if(inv[i]->query("name") == "����������") {zhu = 1; zhu1 = inv[i];}

                }
if( geng && jiding && dusi && zhugan && dongsun && shucai && caomei && niluo && pangxie && doufu && mogu && jiuhu && jiuzhong && fan && zhu )
{
        destruct(geng1);
        destruct(jiding1);
        destruct(dusi1);
        destruct(zhugan1);
        destruct(dongsun1);
        destruct(shucai1);
        destruct(caomei1);
        destruct(niluo1);
        destruct(doufu1);
        destruct(pangxie1);
        destruct(mogu1);
        destruct(jiuhu1);
        destruct(jiuzhong1);
        destruct(fan1);
        destruct(zhu1);
        tuanyuanyanxi = new("/d/city/obj/tuanyuanyanxi");
        tuanyuanyanxi->move(me);
message_vision("$N������ļ������ڰ������Ͼ��İڷ���һ�£��ַ��ϼ�˫
���Ӻ�Щ�ֽ�һ����Բ��ϯŪ���ˣ�\n",this_player());
        
        destruct(this_object());

}
else 
message_vision("$N������ļ����˰ڷ��˼��£�\n",this_player());

return 1;
}

