#!/bin/bash

# 备份路径
backup_base_dir="/mnt/data/db/bkup"
current_year=$(date +%Y)
current_week=$(date +%V)
current_date="$current_year$current_week"  # 当前年份和周序号，例如202301表示2023年第1周

# 函数：执行全量备份
perform_full_backup() {
  # 删除超期数据
  find "$backup_base_dir" -maxdepth 1 -type d -name "week.*" -mtime +28 -exec rm -rf {} \; -exec echo "Deleted backup directory: {}" \;

  # 创建新的全量备份目录
  mkdir -p "$backup_base_dir/week.$current_date/base"

  # 执行全量备份
  xtrabackup --backup --target-dir="$backup_base_dir/week.$current_date/base"

  # 更新软链接为最新的全量备份（相对路径）
  ln -sfnr "$backup_base_dir/week.$current_date/base" "$backup_base_dir/current.base"

  # 更新软链接为最新的备份（相对路径）
  ln -sfnr "$backup_base_dir/week.$current_date/base" "$backup_base_dir/current"
}

# 函数：执行增量备份
perform_incremental_backup() {
  # 检查是否存在当前周的全量备份目录
  if [[ ! -d "$backup_base_dir/week.$current_date/base" ]]; then
    echo "Full backup for the current week is missing. Generating full backup instead of incremental backup."

    perform_full_backup
    exit 0
  fi

  # 获取最新的增量备份序号
  last_delta=$(ls -d "$backup_base_dir/week.$current_date/delta"* 2>/dev/null | awk -F '[.]' '{print $NF}' | sort -n | tail -n 1)
  if [[ -z "$last_delta" ]]; then
    last_delta=0
  fi

  # 创建新的增量备份目录
  mkdir -p "$backup_base_dir/week.$current_date/delta.$((last_delta + 1))"

  # 执行增量备份
  xtrabackup --backup --target-dir="$backup_base_dir/week.$current_date/delta.$((last_delta + 1))" --incremental-basedir="$backup_base_dir/current.base"

  # 更新软链接为最新的增量备份（相对路径）
  ln -sfnr "$backup_base_dir/week.$current_date/delta.$((last_delta + 1))" "$backup_base_dir/current.delta"

  # 更新软链接为最新的备份（相对路径）
  ln -sfnr "$backup_base_dir/week.$current_date/delta.$((last_delta + 1))" "$backup_base_dir/current"
}

# 备份逻辑
if [[ $(date +%u) -eq 1 ]]; then
  # 每周一执行全量备份
  perform_full_backup
else
  # 每日增量备份
  perform_incremental_backup
fi
