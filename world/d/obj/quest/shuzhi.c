//Cracked by Roath
// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
inherit ITEM;
void create()
{
        set_name("����֦", ({"liushu zhi", "shizhi"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "����Ǿ��з�������֦!������ҵ����棲��������
    1�������ƹ���
    2����Ԫ��
Ȼ��Ϳ������(miaohui)��һ�ű���ͼһ��\n");
                set("unit", "��");
               set("owner_name","��������");
               set("owner_id","guanyin pusa");
        }
}


void init()
{
  if(this_player()==environment())
  add_action("do_miaohui","miaohui");
}

int do_miaohui()
{
int i,geng=0,jiding=0;
object tuyi,me, *inv;
object geng1,jiding1;
me = this_player();

inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                {
                        if(inv[i]->query("name") == "�����ƹ���") {geng = 1; geng1 = inv[i];}
                        if(inv[i]->query("name") == "��Ԫ��") {jiding = 1; jiding1 = inv[i];}
                        }
if( geng && jiding)
{
        destruct(geng1);
        destruct(jiding1);
        tuyi = new("/d/city/obj/tu_yi");
        tuyi->move(me);
message_vision("$N�ڱ�����������ҫ�£�����Щ��������һ�ű���ͼ�����üǺš�һ����\n",this_player());
        
        destruct(this_object());

}
else 
message_vision("$NĦ���ű���Ŀ�������\n",this_player());

return 1;
}

