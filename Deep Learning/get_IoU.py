# 传入参数 | bbox_red：红色框坐标 | bbox_green：绿色框坐标
# 注释：坐标格式为(x_left, y_top, x_right, y_bottom)（voc格式坐标，即边框左上角点坐标和右下角点坐标）
def get_IoU(bbox_red, bbox_green):
    # 步骤一：获取交集部分坐标
    ix_min = max(bbox_red[0], bbox_green[0]) # 两个 x_left 中[靠右]的那个
    iy_min = max(bbox_red[1], bbox_green[1]) # 两个 y_top 中[靠下]的那个
    ix_max = min(bbox_red[2], bbox_green[2]) # 两个 x_right 中[靠左]的那个
    iy_max = min(bbox_red[3], bbox_green[3]) # 两个 y_bottom 中[靠上]的那个
    
    # 步骤二：计算交集部分的宽和高
    # 注：可能出现宽度或高度为负数的情况，此时两个框没有交集，交并比为0
    iw = max(ix_max - ix_min, 0.0)
    ih = max(iy_max - iy_min, 0.0)
    
    # 步骤三：计算交集部分面积
    inters = iw * ih
    
    # 步骤四：计算两个框的面积
    # area = w * h = (x_right - x_left) * (y_bottom - y_top)
    red_area = (bbox_red[2] - bbox_red[0]) * (bbox_red[3] - bbox_red[1]) 
    green_area = (bbox_green[2] - bbox_green[0]) * (bbox_green[3] - bbox_green[1]) 
    
    # 步骤五：计算并集面积
    uni = red_area + green_area - inters # 红色框面积 + 绿色框面积 - 交集面积
    
    # 步骤六：计算和返回交并比
    overlaps = inters / uni
    return overlaps

if __name__ == '__main__':
	bbox_red = [9, 3, 16, 10]
	bbox_green = [1, 2, 7, 8]
	print('none: ', get_IoU(bbox_red, bbox_green))