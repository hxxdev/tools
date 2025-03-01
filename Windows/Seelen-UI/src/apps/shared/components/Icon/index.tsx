import { HTMLAttributes } from 'react';

import { cx } from '../../styles';
import InlineSVG from '../InlineSvg';
import cs from './index.module.css';

interface ReactIconProps extends HTMLAttributes<HTMLElement> {
  iconName: string;
  size?: string | number;
  color?: string;
}

/** React Icons */
export function Icon(props: ReactIconProps) {
  const { iconName, size, color, className, ...rest } = props;

  return (
    <InlineSVG
      {...rest}
      src={`../icons/${iconName}.svg`}
      className={cx('slu-icon', cs.reactIcon, className)}
      style={{ height: size, color }}
    />
  );
}

export * from './FileIcon';
export * from './MissingIcon';
export * from './SpecificIcon';