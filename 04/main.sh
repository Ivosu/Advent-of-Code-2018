#!/usr/bin/env bash

_qsort()
{
    (($# == 0)) && {
        unset qreturn
        return
    }

    local pivot="$1"; shift
    local i
    local -a higher
    local -a lower

    for i in "$@"; do
        if [[ "$i" < "${pivot}" ]]; then
            lower+=("$i")
        else
            higher+=("$i")
        fi
    done

    _qsort "${higher[@]}"
    higher=("${qreturn[@]}")

    _qsort "${lower[@]}"
    qreturn+=("${pivot}" "${higher[@]}")
}

qsort()
(
    qreturn=()
    _qsort "$@"
    printf "%s\\n" "${qreturn[@]}"
)

part1()
{
    [[ -f "${PWD}/input" ]] && {
        mapfile -t file < "${PWD}/input"
        mapfile -t file < <(qsort "${file[@]}")

        i="0"
        while ((i < ${#file[@]})); do
            read -r _ _ _ id _ <<< "${file[$i]}"
            id="${id/'#'}"

            if [[ "${midnight_list[$id]}" ]]; then
                read -ra midnight <<< "${midnight_list[$id]}"
            else
                for j in {0..59}; do
                    midnight[$j]="0"
                done
            fi

            ((i++))
            j="0"
            while [[ ! "${file[$i]}" =~ 'Guard' ]] && ((i < ${#file[@]})); do
                ((i++)); ((j++))
            done

            for ((k = i - j; k < i; k++)); do
                read -r _ sleep_time _ <<< "${file[$((k++))]}"
                read -r _ wake_time _ <<< "${file[$k]}"

                sleep_time="${sleep_time/*:}"
                sleep_time="${sleep_time/']'}"
                sleep_time="$((10#${sleep_time}))"

                wake_time="${wake_time/*:}"
                wake_time="${wake_time/']'}"
                wake_time="$((10#${wake_time}))"

                for ((l = sleep_time; l < wake_time; l++)); do
                    ((midnight[l]++))
                done
            done

            printf -v midnight_list[$id] "%d " "${midnight[@]}"
        done

        for id in "${!midnight_list[@]}"; do
            unset total_time
            unset max

            read -ra midnight <<< "${midnight_list[$id]}"
            for i in "${midnight[@]}"; do
                ((total_time += i))
                ((max = i > ${max:=0} ? i : ${max:=0}))
            done

            printf -v midnight_list[$id] "%d " \
                "${total_time}" \
                "${max}" \
                "${midnight[@]}"
        done

        unset max
        for id in "${!midnight_list[@]}"; do
            read -ra midnight <<< "${midnight_list[$id]}"
            ((max = midnight[0] > ${max:=0} ? midnight[0] : ${max:=0}))
        done

        for id in "${!midnight_list[@]}"; do
            max_min="0"
            read -ra midnight <<< "${midnight_list[$id]}"
            ((max == midnight[0])) && \
                for minute in "${midnight[@]:2}"; do
                    if ((midnight[1] != minute)); then
                        ((max_min++))
                    else
                        break 2
                    fi
                done
        done

        printf "ID: %d\\nMinute: %d\\n" "${id}" "${max_min}"
        printf "Part1: %d\\n\\n" "$((id * max_min))"
    }
}

part2()
{
    [[ "${midnight_list[*]}" ]] && {
        unset max
        for id in "${!midnight_list[@]}"; do
            read -ra midnight <<< "${midnight_list[$id]}"
            ((max = midnight[1] > ${max:=0} ? midnight[1] : ${max:=0}))
        done

        for id in "${!midnight_list[@]}"; do
            max_min="0"
            read -ra midnight <<< "${midnight_list[$id]}"
            ((max == midnight[1])) && \
                for minute in "${midnight[@]:2}"; do
                    if ((midnight[1] != minute)); then
                        ((max_min++))
                    else
                        break 2
                    fi
                done
        done

        printf "ID: %d\\nMinute: %d\\n" "${id}" "${max_min}"
        printf "Part2: %d\\n" "$((id * max_min))"
    }
}

main()
{
    part1
    part2
}

main
